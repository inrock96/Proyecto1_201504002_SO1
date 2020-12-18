import time

from locust import HttpUser,task

class QuickstartUser(HttpUser):
    def on_start(self):
        self.client.get("/")