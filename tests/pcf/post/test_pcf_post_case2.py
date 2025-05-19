import copy

import requests

from config import BASE_URL_PCF, HEADERS

# valid by mac
def test_pcf_post_case2(pcf_json_data):
    data = copy.deepcopy(pcf_json_data)
    data.pop("ipv4Addr", None)
    data.pop("ipv6Addr", None)

    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    json = r.json()
    assert r.status_code == 201, f"Expected 201, got {r.status_code}"
    assert "Location" in r.headers
    assert r.headers["Location"].startswith(BASE_URL_PCF)
    assert isinstance(json, dict) or isinstance(json, list)
