import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_get_4_ipv4_add_info_200(prepare_pcf_binding):
    data = {
        "ipv4Addr" : prepare_pcf_binding["ipv4Addr"],
        "supi": prepare_pcf_binding["supi"],
        "dnn": prepare_pcf_binding["dnn"],
        "sst": prepare_pcf_binding["snssai"]["sst"]
        }

    r = requests.get(BASE_URL_PCF, params = data, headers=HEADERS)
    json = r.json()
    assert r.status_code == 200, f"Expected 200, got {r.status_code}"
    assert isinstance(json, dict) or isinstance(json, list)
    assert json.get("supi") == prepare_pcf_binding["supi"]
    assert json.get("ipv4Addr") == prepare_pcf_binding["ipv4Addr"]
