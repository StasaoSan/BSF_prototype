import pytest
import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_delete_3_empty_link_400(prepare_pcf_delete):
    uuid = "" # empty UUID (correct in [prepare_pcf_delete])

    r = requests.delete(BASE_URL_PCF + f"/{uuid}", headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
