import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_get_case6(prepare_pcf_binding):
    data = {
        "macAddr48" : prepare_pcf_binding["macAddr48"],
        "supi": prepare_pcf_binding["dnn"], # here information is incorrect
        "dnn": prepare_pcf_binding["dnn"],
        "sst": prepare_pcf_binding["snssai"]["sst"]
        }

    r = requests.get(BASE_URL_PCF, params = data, headers=HEADERS)
    assert r.status_code == 204, f"Expected 204, got {r.status_code}"
