import copy

import requests

from config import BASE_URL_PCF_UE, HEADERS

# valid post but record with this combination fleet exists
def test_pcf_ue_post_case3(prepare_pcf_ue_binding):
    data = prepare_pcf_ue_binding

    r = requests.post(BASE_URL_PCF_UE, json=data, headers=HEADERS)
    assert r.status_code == 403, f"Expected 403, got {r.status_code}"
