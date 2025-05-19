import requests

from config import BASE_URL_PCF_UE, HEADERS


def test_pcf_ue_delete_case2(prepare_pcf_ue_delete):
    uuid = "" # empty UUID

    r = requests.delete(BASE_URL_PCF_UE + f"/{uuid}", headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
