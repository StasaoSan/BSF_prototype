import requests
from config import BASE_URL_PCF, HEADERS

# valid post but record with this combination fleet exists
def test_pcf_post_5_already_exist_403(prepare_pcf_binding):
    data = prepare_pcf_binding
    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    assert r.status_code == 403, f"Expected 403, got {r.status_code}"