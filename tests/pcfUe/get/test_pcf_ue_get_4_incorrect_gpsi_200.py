import requests

from config import BASE_URL_PCF_UE, HEADERS

def test_pcf_ue_get_4_incorrect_gpsi_200(prepare_pcf_ue_binding):
    data = {
        "gpsi" : prepare_pcf_ue_binding["gpsi"] + "1" # incorrect gpsi (correct without "1")
    }

    r = requests.get(url=BASE_URL_PCF_UE, params=data, headers=HEADERS)
    json = r.json()
    assert r.status_code == 200, f"Expected 200, got {r.status_code}"
    assert isinstance(json, dict) or isinstance(json, list) # json empty assert
