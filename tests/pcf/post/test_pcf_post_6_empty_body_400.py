import requests

from config import BASE_URL_PCF, HEADERS

# empty json body
def test_pcf_post_6_empty_body_400():
    data = { }
    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
