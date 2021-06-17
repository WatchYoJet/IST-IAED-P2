from dhooks import Webhook
import requests
from bs4 import BeautifulSoup
import os
import time
import smtplib
import json

hook = Webhook(
    "https://discord.com/api/webhooks/855051375000027166/cV3iEAr7FgT9dOi2VxAf_1pwvev6NkyXcbOdZVoTUpDEH15ZT7Vsk_-Wa9kVEGfgiKwo"
)

hook.send("Restart completed.\nI'm working!\n<@192012933281087489>")

cadeiras = {
    'https://fenix.tecnico.ulisboa.pt/disciplinas/CMat564511132646/2020-2021/2-semestre':
    'CMAT',  #IAED
    'https://fenix.tecnico.ulisboa.pt/disciplinas/CDI132511132646/2020-2021/2-semestre/':
    'CDI I',  #AL
    'https://fenix.tecnico.ulisboa.pt/disciplinas/CDI46/2020-2021/2-semestre/':
    'CDI II',  #IETI
    'https://fenix.tecnico.ulisboa.pt/disciplinas/DMG764511132646/2020-2021/2-semestre/':
    'DMG',  #AC
    'https://fenix.tecnico.ulisboa.pt/disciplinas/Ges246/2020-2021/2-semestre':
    'GES',  #MO
    'https://fenix.tecnico.ulisboa.pt/disciplinas/MO4364511132646/2020-2021/2-semestre/':
    'MO',
    'https://fenix.tecnico.ulisboa.pt/disciplinas/PPes364511132646/2020-2021/2-semestre/':
    'PPES',
    'https://fenix.tecnico.ulisboa.pt/disciplinas/AL70511132646/2020-2021/2-semestre/':
    'AL',
}


def checker(URL, cadeira):
    headers = {
        'User-Agent':
        'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36'
    }
    try:
        page = requests.get(URL, headers=headers)
        soup = BeautifulSoup(page.content, 'html.parser')
        title = soup.find("h5").get_text()
        title = title.strip()
    except:
        title = ''

    writepath = f'./Hook_meec_{cadeira}.txt'
    mode = 'r' if os.path.exists(writepath) else 'w'
    with open(writepath, mode) as f:
        try:
            f.write(title)
            print(cadeira)
            print(title)
        except:
            pass

    if title == open(writepath).read():
        pote = False
    else:
        pote = title
    return pote


def textDelete(cadeira):
    if os.path.exists(f"./Hook_meec_{cadeira}.txt"):
        os.remove(f"./Hook_meec_{cadeira}.txt")


def hookSend(pings, cadeira, link, title):
    hook.send(f"\nNovo anuncio de {cadeira}!\nTitle: {title}\n{link}")



while True:
    for cadeira in cadeiras.keys():
        pings = ""
        if checker(cadeira, cadeiras[cadeira]):
            hookSend(pings, cadeiras[cadeira], cadeira,
                     checker(cadeira, cadeiras[cadeira]))
            textDelete(cadeiras[cadeira])
    time.sleep(10)