import sys
import requests

def fetch_website(domain_name):
    if not domain_name.startswith('http'):
        url = f"http://{domain_name}"

    print("Connecting...")

    try:
        response = requests.get(url, timeout=5)
        response.raise_for_status()

        print(f"Status Code: {response.status_code}")
        print(response.text)

    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)

    domain_to_check = sys.argv[1]
    fetch_website(domain_to_check)