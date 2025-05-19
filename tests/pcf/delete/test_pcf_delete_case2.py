import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_delete_case2(prepare_pcf_delete):
    uuid = "1234567890" # incorrect UUID (correct in [prepare_pcf_delete])

    r = requests.delete(BASE_URL_PCF + f"/{uuid}", headers=HEADERS)
    assert r.status_code == 404, f"Expected 404, got {r.status_code}"
