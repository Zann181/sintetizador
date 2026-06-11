# Plan de Verificación — Corrección de Sincronización y Estabilidad UI

Este plan detalla los fallos identificados en la refactorización DDD del frontend, las soluciones de ingeniería propuestas y las pruebas de control de calidad para verificar la correcta sincronización.

---

## 1. Problemas Detectados

### A. Auto-cierre de Dropdowns (Menús Desplegables)
* **Síntoma**: Al hacer clic en cualquier selector (`select`) del mezclador (como el selector de Groove o Tonalidad), este se cierra automáticamente antes de poder elegir una opción.
* **Causa**: El intervalo de telemetría de `StateManager` invoca `syncParams()` cada 1 segundo. Al dispararse el evento `paramsChanged`, el archivo `main.js` ejecuta `mixerConsole.render()`, lo que destruye y recrea todo el HTML del Mixer por completo desde cero, cancelando el foco y estado activo del DOM.

### B. Fallo en el Selector de Groove (Secuenciador)
* **Síntoma**: Al intentar seleccionar un Groove preestablecido, la cuadrícula de pasos no se actualiza o el selector se resetea inmediatamente.
* **Causa**: Al cargarse el groove, se actualizan parámetros en el servidor a través de `updateParamValue()`, lo que detona un refresco general de parámetros (`paramsChanged`) y la subsecuente reconstrucción destructiva del Mixer. Además, al reconstruirse el DOM, se pierden los valores visuales seleccionados.

### C. Desaparición del Playhead (Luz Azul del Secuenciador)
* **Síntoma**: La luz azul que indica el paso de reproducción activo en la grilla de pads del secuenciador no se mueve o no aparece.
* **Causa**: En `SequencerService.js`, el método `startPlayhead()` aborta inmediatamente si `hasWebSocketSync` es `true`. Sin embargo, si el servidor WebSocket de sincronización Ableton Link está conectado pero inactivo (no está reproduciendo), la aplicación detiene las consultas de paso HTTP `/api/status`, congelando el playhead.

### D. Ajustes Inoperantes (Settings Panel)
* **Síntoma**: Los interruptores del emulador, BPM de simulación y dispositivo de salida de audio en el panel derecho no reflejan los valores reales del sintetizador.
* **Causa**: La refactorización no vinculó el evento `paramsChanged` con los elementos de control del panel de ajustes, por lo que nunca se actualizan en tiempo real ni leen el estado actual del backend.

---

## 2. Soluciones Propuestas

### Paso 1: Actualizaciones In-Place en MixerConsole
* **Acción**: Implementar el método `updateValues()` dentro de `MixerConsole.js` para modificar faders, displays numéricos, potenciómetros e interruptores directamente sobre los elementos del DOM existentes (usando `document.getElementById`) en lugar de reconstruir todo el HTML con `render()`.
* **Uso**: Modificar el receptor del evento `paramsChanged` en `main.js` para llamar a `mixerConsole.updateValues()` en lugar de `render()`, una vez que el mezclador ha sido dibujado por primera vez.

### Paso 2: Corrección del Intervalo del Playhead
* **Acción**: Eliminar la restricción `|| this.hasWebSocketSync` de la función de intervalo en `startPlayhead()`. Esto asegura que si la sincronización WebSocket está activa pero pausada, el sistema continúe leyendo de forma transparente la posición actual de reproducción de la API HTTP.

### Paso 3: Sincronización In-Place del Panel de Ajustes
* **Acción**: Suscribir a `LcdTelemetry.js` al evento `paramsChanged` para actualizar el estado del emulador (`/emulator/active`, `/emulator/bpm`) y del BPM global (`/master/bpm`) directamente sobre los elementos input del DOM de ajustes, respetando si el usuario los está editando activamente.

---

## 3. Matriz de Pruebas de Verificación

| ID | Caso de Prueba | Procedimiento de Prueba | Resultado Esperado |
|---|---|---|---|
| **TC-01** | Persistencia de Dropdowns | Abrir el menú "Groove" o "Tonalidad" en cualquier canal del Mixer y esperar > 2 segundos sin seleccionar nada. | El menú desplegable debe permanecer abierto y enfocado sin cerrarse automáticamente. |
| **TC-02** | Carga de Groove local | Seleccionar un patrón de la lista (ej. "Tribu") en el selector de Groove del Mixer o Secuenciador. | Los pads del instrumento deben encenderse/apagarse según el patrón y el selector debe mostrar el nombre del groove. |
| **TC-03** | Movimiento del Playhead | Cambiar a la vista de Secuenciador (Pads) mientras el motor de síntesis está en reproducción. | Una luz azul deslizante debe avanzar continuamente a través de los pasos 1 a 16. |
| **TC-04** | Sincronización de Ajustes | Activar/desactivar el "Link Sync Emulator" o variar el "BPM Emu" en la barra lateral de Ajustes. | El estado de los controles de simulación debe persistir y actualizarse correctamente al recargar la página. |
| **TC-05** | Arrastre de Potenciómetros | Hacer clic y arrastrar los mandos de "Accent" o "Swing" en el mezclador de forma continua. | El control debe deslizarse suavemente sin tirones ni pérdidas de foco de ratón. |
