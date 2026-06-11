#pragma once
#include "IInstrumentVoice.h"
#include "InstrumentDescriptor.h"
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

// ============================================================================
// VoiceFactory.h
// Registry dinámico para crear instancias de instrumentos por nombre.
// Permite intercambiar voces en caliente como módulos de plugin.
//
// Uso típico:
//   VoiceFactory factory;
//   factory.registerVoice<KickVoice>("kick_808");
//   factory.registerVoice<Kick909Voice>("kick_909");
//
//   auto kick = factory.create("kick_808");
//   kick->initialize(44100.0);
//
//   // Intercambiar en el slot 0 del sintetizador:
//   m_voices[0] = factory.create("kick_909");
//   m_voices[0]->initialize(m_sampleRate);
// ============================================================================

namespace bazz {

class VoiceFactory {
public:
    // Tipo de función constructora
    using Creator = std::function<std::shared_ptr<IInstrumentVoice>()>;

    // ---- Registro de voces ----

    // Registra un tipo de instrumento con su nombre de tipo.
    // El nombre debe coincidir con InstrumentDescriptor::typeName.
    template<typename T>
    void registerVoice() {
        // Crear instancia temporal para obtener el descriptor
        auto temp = std::make_shared<T>();
        // Nota: no inicializamos con sampleRate aquí, solo obtenemos metadatos
        const auto& desc = temp->getDescriptor();
        std::string name(desc.typeName);

        m_creators[name] = []() -> std::shared_ptr<IInstrumentVoice> {
            return std::make_shared<T>();
        };
        m_descriptors[name] = &temp->getDescriptor();
        m_registeredNames.push_back(name);

        // Almacenar la instancia temporal para mantener vivo el descriptor
        m_protoInstances[name] = std::move(temp);
    }

    // Registra un tipo de instrumento con un nombre explícito (override).
    template<typename T>
    void registerVoice(const std::string& overrideName) {
        m_creators[overrideName] = []() -> std::shared_ptr<IInstrumentVoice> {
            return std::make_shared<T>();
        };
        m_registeredNames.push_back(overrideName);
    }

    // ---- Creación de instancias ----

    // Crea una nueva instancia del instrumento por su nombre de tipo.
    // Retorna nullptr si el nombre no está registrado.
    std::shared_ptr<IInstrumentVoice> create(const std::string& typeName) const {
        auto it = m_creators.find(typeName);
        if (it == m_creators.end()) return nullptr;
        return it->second();
    }

    // ---- Consultas ----

    // Retorna la lista de nombres de tipos registrados.
    const std::vector<std::string>& listAvailable() const {
        return m_registeredNames;
    }

    // Verifica si un tipo de instrumento está registrado.
    bool isRegistered(const std::string& typeName) const {
        return m_creators.find(typeName) != m_creators.end();
    }

    // Obtiene el descriptor de un tipo registrado (puede ser nullptr).
    const InstrumentDescriptor* getDescriptor(const std::string& typeName) const {
        auto it = m_descriptors.find(typeName);
        if (it == m_descriptors.end()) return nullptr;
        return it->second;
    }

    // Retorna la cantidad de tipos registrados.
    size_t count() const { return m_creators.size(); }

private:
    std::unordered_map<std::string, Creator> m_creators;
    std::unordered_map<std::string, const InstrumentDescriptor*> m_descriptors;
    std::unordered_map<std::string, std::shared_ptr<IInstrumentVoice>> m_protoInstances;
    std::vector<std::string> m_registeredNames;
};

// ============================================================================
// VoiceSlot — un slot que contiene una voz activa con su reloj y estado
// Facilita intercambiar voces en caliente manteniendo la configuración del slot
// ============================================================================

struct VoiceSlot {
    std::shared_ptr<IInstrumentVoice> voice;
    std::string typeName;       // Tipo actual de la voz
    int sequencerChannel = -1;  // Canal del secuenciador (0-5)
    bool active = true;         // Si el slot está habilitado
    float volume = 1.0f;        // Volumen del slot en el mezclador
    float pan = 0.0f;           // Paneo (-1.0 = izq, 0.0 = centro, 1.0 = der)

    // Intercambia la voz en este slot por una nueva del factory.
    // Preserva el canal del secuenciador y la configuración del slot.
    bool swapVoice(const VoiceFactory& factory, const std::string& newTypeName, double sampleRate) {
        auto newVoice = factory.create(newTypeName);
        if (!newVoice) return false;

        newVoice->initialize(sampleRate);
        voice = std::move(newVoice);
        typeName = newTypeName;
        return true;
    }
};

} // namespace bazz
