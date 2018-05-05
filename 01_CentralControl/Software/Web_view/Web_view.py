# coding:utf-8

from flask import render_template, jsonify, request
from Db_operation import app, db, Num


@app.route('/', methods=['GET', 'POST'])
def test_base():
    if request.method == 'POST':
        return jsonify('test')
    return render_template("index.html", title_name='welcome')


@app.route('/table', methods=['GET', 'POST'])
def show_table():
    if request.method == 'POST':
        return jsonify(render_template("table.html"))
    return jsonify("busy")


@app.route('/chart', methods=['GET', 'POST'])
def show_chart():
    if request.method == 'POST':
        global db
        counter = Num.query.order_by(Num.id.desc()).limit(1).first().number + 1
        db.session.add(Num(number=counter))
        db.session.commit()
        return jsonify(render_template("chart.html", **locals()))
    return jsonify("busy")


if __name__ == '__main__':
    db.create_all()
    db.session.add(Num(number=1))
    db.session.commit()
    app.run(port=8080, debug=True)




