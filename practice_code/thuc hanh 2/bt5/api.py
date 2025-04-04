from flask import Flask, request, jsonify, url_for, redirect
import json
import atexit
from waitress import serve


app = Flask(__name__)
app.config["DEBUG"] = False

# open import and close db.json
readFile = open("db.json", 'r')
data = json.load(readFile)
readFile.close()

# adding exit routine to save the db.json file with the current states (not really necessary but is nice for debugging)

def exit_routine():
    print("Terminating server")
    writeFile = open(r"F:\StudyatCLass\Study\class\CongngheIOT\thuc hanh\thuc hanh 2\bt5\db.json", "w")
    writeFile.write(json.dumps(data, indent=4, sort_keys=True))
    writeFile.close()

atexit.register(exit_routine)
# default route
@app.route("/", methods=["GET"])
def home():
    return "Thay Thuyen vjp pro"


@app.route("/robots/<id>", methods=["GET", "PUT"])
def robot(id):
    id = int(id)
    if request.method == "GET":
        if id > 0 and id <= len(data["robots"]):
            return jsonify(data["robots"][id-1])
    if request.method == "PUT":
        if id > 0 and id <= len(data["robots"]):
            data["robots"][id-1] = request.json
            return jsonify(data["robots"][id-1])
        
@app.route("/robots/command/<id>", methods=["GET", "PUT"])
def robotCommand(id):
    id = int(id)
    if request.method == "GET":
        if id > 0 and id <= len(data["robotCommand"]):
            return jsonify(data["robotCommand"][id-1])
    if request.method == "PUT":
        if id > 0 and id <= len(data["robotCommand"]):
            data["robotCommand"][id-1] = request.json
            return jsonify(data["robotCommand"][id-1])


serve(app, host="192.168.0.109", port=3000, threads=4)