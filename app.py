from flask import Flask,redirect,render_template,request
import pyrebase
import re


formate = r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'


app = Flask(__name__)

config = {
    "apiKey": "AIzaSyBcQr-xm0gqX0C0eB025v63feoRXRyx6dM",
    "authDomain": "team-expansion-54ae7.firebaseapp.com",
    "databaseURL": "https://team-expansion-54ae7-default-rtdb.firebaseio.com",
    "projectId": "team-expansion-54ae7",
    "storageBucket": "team-expansion-54ae7.appspot.com",
    "messagingSenderId": "932038990518",
    "appId": "1:932038990518:web:02f65a0122d0ff39bfa417",
    "measurementId": "G-NCB4XT3N2C"
    }

firebase = pyrebase.initialize_app(config)
database = firebase.database()


@app.route("/",methods=["POST","GET"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        mail = request.form.get("mail")
        mobile = request.form.get("mobile")
        subject = request.form.get("subject")
        message = request.form.get("message")
        if ((re.fullmatch(formate, mail)) != None) and ((re.fullmatch('[6-9][0-9]{9}',mobile)) != None) and  (name != "") and (subject != "")  and (message!= "") :
            data = {
                "name" : name,
                "mail" : mail,
                "mobile" : mobile,
                "subject" : subject,
                "message" : message,
            }
            database.child("all_data").push(data)
            return redirect("/success")
        else :
            return redirect("/failure")

    else :
        return render_template("form.html")

@app.route("/success",methods=["POST","GET"])
def success():
    if request.method == "POST":
        return redirect("/")
    else:
        return render_template("success.html")


@app.route("/failure",methods=["POST","GET"])
def failure():
    if request.method == "POST":
        return redirect("/")
    else:
        return render_template("failure.html")


if __name__ == "__main__":
    app.run(debug=True)

