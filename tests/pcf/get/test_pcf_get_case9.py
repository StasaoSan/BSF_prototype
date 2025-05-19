import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_get_case9(prepare_pcf_binding):
    data = {
        "macAddr48" : prepare_pcf_binding["macAddr48"]+"12", # + "12" -  information is incorrect
        "supi": prepare_pcf_binding["supi"],
        "dnn": prepare_pcf_binding["dnn"],
        "sst": prepare_pcf_binding["snssai"]["sst"]
        }

    r = requests.get(BASE_URL_PCF, params = data, headers=HEADERS)
    assert r.status_code == 404, f"Expected 404, got {r.status_code}"
