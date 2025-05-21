import copy

import requests

from config import BASE_URL_PCF_UE, HEADERS

# empty body
def test_pcf_ue_post_4_empty_body_400():
    data = {}

    r = requests.post(BASE_URL_PCF_UE, json=data, headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
