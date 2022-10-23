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

cred = credentials.Certificate("./server-arduino-with-python-firebase-adminsdk-pc9nr-929e421501.json")
firebase_admin.initialize_app(cred,{
    'dateabaseURL' : 'https://server-arduino-with-python-default-rtdb.firebaseio.com/'
})

@app.get("/temp/{temps}/Humidity/{humidity}",response_class=HTMLResponse)
async def read_th(request: Request,temps: int,humidity: int):
    #ref = db.reference('온습도') #경로가 없으면 생성한다.
    #ref.update({'온도' : temps})
    #ref.update({'습도' : humidity}) 
    ref= db.reference('/')
    ref.update({'온도' : temps})
    ref.update({'습도' : humidity})
    return templates.TemplateResponse("index.html",{"request":request,"temps":temps,"humidity":humidity})

# @app.get("/totlal",response_class=HTMLResponse)
# def read_total(request: Request):
#     ref = db.reference('강좌/파이썬')
