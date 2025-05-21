import requests

from config import BASE_URL_PCF_UE, HEADERS


def test_pcf_ue_delete_1_vaild_204(prepare_pcf_ue_delete):
    uuid = prepare_pcf_ue_delete

    r = requests.delete(BASE_URL_PCF_UE + f"/{uuid}", headers=HEADERS)
    assert r.status_code == 204, f"Expected 204, got {r.status_code}"
