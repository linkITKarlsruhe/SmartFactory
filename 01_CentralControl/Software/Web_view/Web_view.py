# coding:utf-8

from flask import Flask, render_template, jsonify, request
# from flask_bootstrap import Bootstrap

app = Flask(__name__)
# Bootstrap(app)


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
        return jsonify(render_template("chart.html"))
    return jsonify("busy1")

if __name__ == '__main__':
    app.run(port=8080, debug=True)



