# coding:utf-8

from flask import Flask
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:////home/peiren/test.db'
db = SQLAlchemy(app)


class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    battery_status = db.Column(db.Integer,
                               db.CheckConstraint('battery_status BETWEEN 0 and 100'))

    def __repr__(self):
        return '%r' % [self.id, self.battery_status]


class FTS(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    sensor1 = db.Column(db.Integer, db.CheckConstraint('sensor1 BETWEEN 0 and 1000'))
    sensor2 = db.Column(db.Integer, db.CheckConstraint('sensor2 BETWEEN 0 and 1000'))
    sensor3 = db.Column(db.Integer, db.CheckConstraint('sensor3 BETWEEN 0 and 1000'))
    sensor4 = db.Column(db.Integer, db.CheckConstraint('sensor4 BETWEEN 0 and 1000'))
    sensor5 = db.Column(db.Integer, db.CheckConstraint('sensor5 BETWEEN 0 and 1000'))
    sensor6 = db.Column(db.Integer, db.CheckConstraint('sensor6 BETWEEN 0 and 1000'))
    sensor7 = db.Column(db.Integer, db.CheckConstraint('sensor7 BETWEEN 0 and 1000'))
    sensor8 = db.Column(db.Integer, db.CheckConstraint('sensor8 BETWEEN 0 and 1000'))

    calibration1 = db.Column(db.Integer, db.CheckConstraint('calibration1 BETWEEN 0 and 2500'))
    calibration2 = db.Column(db.Integer, db.CheckConstraint('calibration2 BETWEEN 0 and 2500'))
    calibration3 = db.Column(db.Integer, db.CheckConstraint('calibration3 BETWEEN 0 and 2500'))
    calibration4 = db.Column(db.Integer, db.CheckConstraint('calibration4 BETWEEN 0 and 2500'))
    calibration5 = db.Column(db.Integer, db.CheckConstraint('calibration5 BETWEEN 0 and 2500'))
    calibration6 = db.Column(db.Integer, db.CheckConstraint('calibration6 BETWEEN 0 and 2500'))
    calibration7 = db.Column(db.Integer, db.CheckConstraint('calibration7 BETWEEN 0 and 2500'))
    calibration8 = db.Column(db.Integer, db.CheckConstraint('calibration8 BETWEEN 0 and 2500'))

    pulse_width_modulation_left = db.Column(db.Integer,
                                            db.CheckConstraint('pulse_width_modulation_left BETWEEN 0 and 255'))
    pulse_width_modulation_right = db.Column(db.Integer,
                                             db.CheckConstraint('pulse_width_modulation_right BETWEEN 0 and 255'))
    # True = is moving, False = stopped
    is_driving = db.Column(db.Boolean)
    # True = Closed, False = Open
    door_status = db.Column(db.Boolean)
    battery_status = db.Column(db.Integer,
                               db.CheckConstraint('battery_status BETWEEN 0 and 100'),
                               nullable=False)

    def __repr__(self):
        return '%r' % {'sensor1': self.sensor1, 'sensor2': self.sensor2, 'sensor3': self.sensor3,
                       'sensor4': self.sensor4, 'sensor5': self.sensor5, 'sensor6': self.sensor6,
                       'sensor7': self.sensor7, 'sensor8': self.sensor8,
                       'calibration1': self.calibration1, 'calibration2': self.calibration2,
                       'calibration3': self.calibration3, 'calibration4': self.calibration4,
                       'calibration5': self.calibration5, 'calibration6': self.calibration6,
                       'calibration7': self.calibration7, 'calibration8': self.calibration8,
                       'pulse_width_modulation_left': self.pulse_width_modulation_left,
                       'pulse_width_modulation_right': self.pulse_width_modulation_right,
                       'is_driving': self.is_driving, 'door_status': self.door_status,
                       'battery_status': self.battery_status}


if __name__ == "__main__":
    db.create_all()
    data = {'sensor1': 200, 'sensor2': 100, 'sensor3': 200, 'sensor4': 243,
            'sensor5': 500, 'sensor6': 800, 'sensor7': 999, 'sensor8': 900,
            'calibration1': 2100, 'calibration2': 1000, 'calibration3': 2020,
            'calibration4': 2300, 'calibration5': 200, 'calibration6': 2000,
            'calibration7': 2400, 'calibration8': 1000,
            'pulse_width_modulation_left': 244, 'pulse_width_modulation_right': 13,
            'is_driving': True, 'door_status': False, 'battery_status': 98}
    test_data = FTS(**data)
    db.session.add(test_data)
    db.session.commit()
    print(FTS.query.all()[0])