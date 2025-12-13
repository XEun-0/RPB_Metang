
# curl -F "file=@paylabel.pdf" http://172.23.41.178:8080/upload
# curl -F "file=@paylabel.pdf" http://192.168.1.31:8080/upload
# curl -O http://192.168.1.31:8080/uploads/paylabel.pdf
# curl -O http://192.168.1.31:8080/paylabel.pdf
#!/usr/bin/env python3
import http.server
import socketserver
import cgi
import os
import socket

PORT = 8080
UPLOAD_DIR = "uploads"

class Handler(http.server.SimpleHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/upload':
            os.makedirs(UPLOAD_DIR, exist_ok=True)
            form = cgi.FieldStorage(
                fp=self.rfile,
                headers=self.headers,
                environ={'REQUEST_METHOD': 'POST',
                         'CONTENT_TYPE': self.headers['Content-Type']}
            )

            if "file" in form:
                file_item = form["file"]
                filename = os.path.basename(file_item.filename)
                filepath = os.path.join(UPLOAD_DIR, filename)

                with open(filepath, "wb") as f:
                    f.write(file_item.file.read())

                print(f"[+] Uploaded: {filename}")
                self.send_response(200)
                self.end_headers()
                self.wfile.write(b"Upload successful\n")
            else:
                self.send_response(400)
                self.end_headers()
                self.wfile.write(b"No file provided\n")
        else:
            self.send_response(404)
            self.end_headers()

def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
    except Exception:
        ip = "127.0.0.1"
    finally:
        s.close()
    return ip

if __name__ == "__main__":
    ip = get_ip()
    print(f"Server running at: http://{ip}:{PORT}")
    print(f"Upload via: curl -F \"file=@yourfile.txt\" http://{ip}:{PORT}/upload")
    print(f"Download via: curl -O http://{ip}:{PORT}/filename")
    os.makedirs(UPLOAD_DIR, exist_ok=True)

    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        print("[*] Waiting for requests...")
        httpd.serve_forever()
