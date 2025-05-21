import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_get_2_vaild_macAddr_200(prepare_pcf_binding):
    data = {
        "macAddr48": prepare_pcf_binding["macAddr48"]
    }

    r = requests.get(BASE_URL_PCF, params = data, headers=HEADERS)
    json = r.json()
    assert r.status_code == 200, f"Expected 200, got {r.status_code}"

    assert isinstance(json, dict) or isinstance(json, list)
