import os

file_path = r"c:\Users\Motaz\Music\Nueva carpeta\sintetizador\untitled.cpp"

with open(file_path, "r", encoding="utf-8") as f:
    content = f.read()

# 1. Insert headers
math_include = "#include <math.h>"
target_include = '#include <math.h>\n#include "core/FaustDefs.h"\n#include "audio/FaustUI.h"'

if math_include in content and "core/FaustDefs.h" not in content:
    content = content.replace(math_include, target_include, 1)
    print("Injected Faust headers successfully!")

# 2. Append factory functions
end_block = "};\n\n#endif"
target_end_block = """};

extern "C" dsp* newmydsp() {
    return new mydsp();
}

extern "C" void deletemydsp(dsp* d) {
    delete d;
}

#endif"""

if end_block in content:
    content = content.replace(end_block, target_end_block, 1)
    print("Appended newmydsp / deletemydsp successfully!")
else:
    # try with different whitespace
    end_block_alt = "};\n#endif"
    if end_block_alt in content:
        content = content.replace(end_block_alt, target_end_block, 1)
        print("Appended newmydsp / deletemydsp successfully (alt)!")

with open(file_path, "w", encoding="utf-8") as f:
    f.write(content)

print("untitled.cpp headers and exports fixed!")
