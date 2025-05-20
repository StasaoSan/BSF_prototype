import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_get_case3(prepare_pcf_binding):
    data = {
        "ipv6Addr": prepare_pcf_binding["ipv6Addr"]
    }

    r = requests.get(BASE_URL_PCF, params = data, headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
