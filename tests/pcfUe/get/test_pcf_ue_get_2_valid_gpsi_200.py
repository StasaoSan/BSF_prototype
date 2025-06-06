import requests

from config import BASE_URL_PCF_UE, HEADERS

def test_pcf_ue_get_2_valid_gpsi_200(prepare_pcf_ue_binding):
    data = {
        "gpsi" : prepare_pcf_ue_binding["gpsi"]
    }

    r = requests.get(url=BASE_URL_PCF_UE, params=data, headers=HEADERS)
    json = r.json()
    assert r.status_code == 200, f"Expected 200, got {r.status_code}"
    assert isinstance(json, dict) or isinstance(json, list) # json not empty

