import requests
from config import BASE_URL_PCF, HEADERS

def test_pcf_post_case5(prepare_pcf_binding):
    data = prepare_pcf_binding
    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    assert r.status_code == 403, f"Expected 403, got {r.status_code}"