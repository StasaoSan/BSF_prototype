# file for autostart binary file for cpp server
import time
import pytest
import serverControl
import requests
from config import BASE_URL_PCF, HEADERS, BASE_URL_PCF_UE, BASE_PCF_BINDING_JSON, BASE_PCF_UE_BINDING_JSON


@pytest.fixture(scope="function", autouse=True)
def server():
    proc = serverControl.startServer()
    time.sleep(2)
    yield proc
    serverControl.stopServer(proc)


# --------------- PCF BINDING FIXTURES
@pytest.fixture()
def pcf_json_data():
    return BASE_PCF_BINDING_JSON

@pytest.fixture()
def prepare_pcf_binding(pcf_json_data):
    r = requests.post(BASE_URL_PCF, json=pcf_json_data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return pcf_json_data


@pytest.fixture()
def prepare_pcf_delete(pcf_json_data):
    r = requests.post(BASE_URL_PCF, json=pcf_json_data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return r.headers.get("Location").split("/")[-1]

# --------------- PCF UE BINDING FIXTURES
@pytest.fixture()
def pcf_ue_json_data():
    return BASE_PCF_UE_BINDING_JSON

@pytest.fixture()
def prepare_pcf_ue_binding(pcf_ue_json_data):
    r = requests.post(BASE_URL_PCF_UE, json=pcf_ue_json_data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return pcf_ue_json_data

@pytest.fixture()
def prepare_pcf_ue_delete(pcf_ue_json_data):
    r = requests.post(BASE_URL_PCF_UE, json=pcf_ue_json_data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return r.headers.get("Location").split("/")[-1]