from http.server import BaseHTTPRequestHandler, HTTPServer
import requests

# Konfigurasi
BACKEND_SERVER_IP = "192.168.100.20"
BACKEND_SERVER_PORT = 8080
PROXY_PORT = 80

class ReverseProxyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        backend_url = f"http://{BACKEND_SERVER_IP}:{BACKEND_SERVER_PORT}{self.path}"
        print("Sedang meneruskan...")
        try:
            resp = requests.get(backend_url, headers=self.headers, stream=True)

            self.send_response(resp.status_code)

            for key, value in resp.headers.items():
                if key.lower() not in ['content-encoding', 'transfer-encoding']:
                     self.send_header(key, value)
            self.end_headers()

            self.wfile.write(resp.content)

        except requests.ConnectionError:
            self.send_error(502, "Proxy Error")

def run_proxy():
    server_address = ('', PROXY_PORT)
    httpd = HTTPServer(server_address, ReverseProxyHandler)
    print("Reverse Proxy running")
    httpd.serve_forever()

if __name__ == '__main__':
    run_proxy()