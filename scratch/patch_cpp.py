import os
import subprocess

def main():
    dsp_file = "untitled.dsp"
    raw_cpp = "untitled_raw.cpp"
    out_cpp = "untitled.cpp"

    print("1. Compilando untitled.dsp con Faust...")
    cmd = [
        "faust", "-lang", "cpp",
        "-fpga-mem-th", "4", "-ct", "1", "-es", "1",
        "-mcd", "16", "-mdd", "1024", "-mdy", "33",
        "-single", "-ftz", "0",
        dsp_file, "-o", raw_cpp
    ]
    subprocess.run(cmd, check=True)

    print("2. Leyendo el C++ crudo generado...")
    with open(raw_cpp, "r", encoding="utf-8") as f:
        content = f.read()

    print("3. Inyectando cabeceras personalizadas...")
    # Buscamos #include <math.h> e inyectamos después de él
    target_inc = "#include <math.h>"
    if target_inc in content:
        idx = content.find(target_inc) + len(target_inc)
        headers = "\n#include <chrono>\n#include <atomic>\n#include \"core/FaustDefs.h\"\n#include \"audio/FaustUI.h\""
        content = content[:idx] + headers + content[idx:]
    else:
        print("Error: No se encontró #include <math.h> en el código generado.")
        return

    print("4. Inyectando funciones C extern al final...")
    # Buscamos el último #endif e inyectamos justo antes de él
    last_endif_idx = content.rfind("#endif")
    if last_endif_idx != -1:
        externs = """
extern "C" dsp* newmydsp() {
    return new mydsp();
}

extern "C" void deletemydsp(dsp* d) {
    delete d;
}

"""
        content = content[:last_endif_idx] + externs + content[last_endif_idx:]
    else:
        print("Error: No se encontró #endif al final del archivo.")
        return

    print(f"5. Escribiendo resultado final en {out_cpp}...")
    with open(out_cpp, "w", encoding="utf-8") as f:
        f.write(content)

    print("6. Limpiando archivos temporales...")
    if os.path.exists(raw_cpp):
        os.remove(raw_cpp)

    print("¡Listo! untitled.cpp ha sido generado y parcheado con éxito.")

if __name__ == "__main__":
    main()
