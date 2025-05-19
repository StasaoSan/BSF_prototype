import requests

from config import BASE_URL_PCF_UE, HEADERS


def test_pcf_ue_delete_case2(prepare_pcf_ue_delete):
    uuid = "123" # incorrect UUID

    r = requests.delete(BASE_URL_PCF_UE + f"/{uuid}", headers=HEADERS)
    assert r.status_code == 404, f"Expected 404, got {r.status_code}"
