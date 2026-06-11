import urllib.request

try:
    url = "http://localhost:8000/src/main.js"
    req = urllib.request.Request(url, method="HEAD")
    with urllib.request.urlopen(req) as resp:
        print("STATUS:", resp.status)
        print("HEADERS:")
        for k, v in resp.headers.items():
            print(f"  {k}: {v}")
except Exception as e:
    print("ERROR:", e)
