# coding:utf-8

from flask import render_template, jsonify, request
from Db_operation import app, db, FTS
import socket


@app.route('/', methods=['GET', 'POST'])
def test_base():
    if request.method == 'POST':
        return jsonify('test')
    return render_template("index.html", title_name='welcome')


@app.route('/table', methods=['GET', 'POST'])
def show_table():
    if request.method == 'POST':
        column_names = FTS.get_column_names()
        data_rows = FTS.query.limit(1000).all()
        return jsonify(render_template("table.html", **locals()))
    return jsonify("busy")


@app.route('/chart', methods=['GET', 'POST'])
def show_chart():
    if request.method == 'POST':
        # counter = Num.query.order_by(Num.id.desc()).limit(1).first().number + 1
        # db.session.add(Num(number=counter))
        # db.session.commit()
        return jsonify(render_template("chart.html", **locals()))
    return jsonify("busy")


if __name__ == '__main__':
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(("1.1.1.1", 80))
    ipaddr = s.getsockname()[0]
    db.create_all()
    app.run(host=ipaddr, port=8080, debug=True)




