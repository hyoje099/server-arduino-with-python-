from re import template
from typing import Union
from urllib import response

from fastapi import FastAPI,Request
from fastapi.responses import HTMLResponse
from fastapi.templating import Jinja2Templates
import time
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

app = FastAPI()
templates = Jinja2Templates(directory="templates")

@app.get("/")
def read_root():
    return{"Hello":"Wold"}

@app.get("/temp/{temps}/Humidity{humidity}",response_class=HTMLResponse)
def read_th(request: Request,temps: str,humidity: int):
    ref= db.reference(f"/{temps}")
    ref.set(f"{humidity}")
    return templates.TemplateResponse("index.html",{"request":request,"temps":temps,"humidity":humidity})



cred = credentials.Certificate("./server-arduino-with-python-firebase-adminsdk-pc9nr-81c9ad6e13.json")
firebase_admin.initialize_app(cred,{
    'dateabaseURL' : 'https://server-arduino-with-python-default-rtdb.firebaseio.com/'
})
