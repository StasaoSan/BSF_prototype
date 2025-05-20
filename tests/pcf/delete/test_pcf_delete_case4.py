import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_delete_case3(prepare_pcf_delete):
    uuid = "hello" # incorrect UUID type (correct in [prepare_pcf_delete])

    r = requests.delete(BASE_URL_PCF + f"/{uuid}", headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
