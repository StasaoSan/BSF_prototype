import requests

from config import BASE_URL_PCF_UE, HEADERS

def test_pcf_ue_get_3_incorrect_supi_200(prepare_pcf_ue_binding):
    data = {
        "supi" : prepare_pcf_ue_binding["supi"] + "1" # incorrect supi (correct without "1")
    }

    r = requests.get(url=BASE_URL_PCF_UE, params=data, headers=HEADERS)
    json = r.json()
    assert r.status_code == 200, f"Expected 200, got {r.status_code}"
    assert isinstance(json, dict) or isinstance(json, list) # json empty assert
