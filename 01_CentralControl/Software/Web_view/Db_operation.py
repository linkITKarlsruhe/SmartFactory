# coding:utf-8

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
# from flask_bootstrap import Bootstrap

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:////home/peiren/test.db'
db = SQLAlchemy(app)


class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)

    def __repr__(self):
        return '<User %r>' % self.username


class Num(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    number = db.Column(db.Integer)

    def __repr__(self):
        return '%r' % self.number

