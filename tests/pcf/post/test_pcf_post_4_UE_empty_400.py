import copy

import requests
from config import BASE_URL_PCF, HEADERS

# empty UE fleed
def test_pcf_post_4_UE_empty_400(pcf_json_data):
    data = copy.deepcopy(pcf_json_data)
    data.pop("ipv4Addr", None)
    data.pop("ipv6Addr", None)
    data.pop("macAddr48", None)
    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"