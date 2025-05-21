import copy

import requests

from config import BASE_URL_PCF_UE, HEADERS

# empty UE fleed
def test_pcf_ue_post_2_UE_empty_400(pcf_ue_json_data):
    data = copy.deepcopy(pcf_ue_json_data)
    data.pop("supi", None)

    r = requests.post(BASE_URL_PCF_UE, json=data, headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
