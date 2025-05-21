import requests

from config import BASE_URL_PCF_UE, HEADERS

# valid post
def test_pcf_ue_post_1_valid_201(pcf_ue_json_data):
    data = pcf_ue_json_data

    r = requests.post(BASE_URL_PCF_UE, json=data, headers=HEADERS)
    json = r.json()
    assert r.status_code == 201, f"Expected 201, got {r.status_code}"
    assert isinstance(json, dict) or isinstance(json, list)
