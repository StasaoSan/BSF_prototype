import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_delete_case1(prepare_pcf_delete):
    uuid = prepare_pcf_delete

    r = requests.delete(BASE_URL_PCF + f"/{uuid}", headers=HEADERS)
    assert r.status_code == 204, f"Expected 204, got {r.status_code}"
