import os

html_path = r"c:\Users\Motaz\Music\Nueva carpeta\sintetizador\web\index.html"
with open(html_path, "r", encoding="utf-8") as f:
    content = f.read()

start_tag = "<script>"
end_tag = "</script>"

start_idx = content.rfind(start_tag)
end_idx = content.rfind(end_tag)

if start_idx != -1 and end_idx != -1 and start_idx < end_idx:
    new_content = content[:start_idx] + '<script type="module" src="src/main.js"></script>' + content[end_idx + len(end_tag):]
    with open(html_path, "w", encoding="utf-8") as f:
        f.write(new_content)
    print("REFACTOR SUCCESS")
else:
    print("ERROR: Tags not found or misaligned")
