import requests

from config import BASE_URL_PCF_UE, HEADERS


def test_pcf_ue_delete_4_incorrect_type_UUID_400(prepare_pcf_ue_delete):
    uuid = "hello" # incorrect type UUID

    r = requests.delete(BASE_URL_PCF_UE + f"/{uuid}", headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
