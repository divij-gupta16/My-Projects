// Constants
var e = -80/100;
var g = 0.65;
var mu = 0.09;
var cd = 0.9;
var rho = 0.9;

var coin;
var gravity;
var f;
var moment;
var csvFileData = "Time,x,y,z";
var t;
var ax;
var ay;
var az;

function setup() {
  createCanvas(1000, 600, WEBGL);
  coin = new Coin();
  angleMode(RADIANS);
}

class Coin {
  constructor() {
    this.mass = 200;
    this.radius = 30;
    this.height = 10;
    this.diagonal = sqrt((this.radius * this.radius) + (this.height/2 * this.height/2));
    this.weight = this.mass * g;
    this.moi = createVector(1/12 * this.mass * ((3 * this.radius * this.radius) + (this.height * this.height)), 1/2 * this.mass * this.radius * this.radius);
    this.pos = createVector(this.radius, this.height/2, 0);
    this.velocity = createVector(5, 0, 0);
    this.acceleration = createVector(0, 0, 0);
    this.apos = createVector(0, 0, 0);
    this.avel = createVector(0, 0, 0.01);
    this.aa = createVector(0, 0, 0);
    this.torque = createVector(this.weight / this.moi.x, this.weight / this.moi.y, this.weight / this.moi.x);
    this.dycogz = 0.0;
    this.dxcogz = 0.0;
    this.dycogx = 0.0;
    this.dycog = 0.0;
    this.perpdz = 0.0;
    this.area = (2 * PI * this.radius * this.radius) + (PI * this.radius * this.radius * this.height);
  }

  applyForce(force) {
    f = p5.Vector.div(force, this.mass);
    this.acceleration.add(f);
  }

  update() {
      this.velocity.add(this.acceleration.x, this.acceleration.y, this.acceleration.z);
      this.pos.add(this.velocity.x, this.velocity.y, this.velocity.z);
      this.avel.add(this.aa.x, this.aa.y, this.aa.z);
      this.apos.add(this.avel.x, this.avel.y, this.avel.z);
      this.dycogz = abs((this.height/2) * cos(this.apos.z)) + abs(this.radius * sin(this.apos.z));
      this.dxcogz = abs((this.height/2) * sin(this.apos.z)) + abs(this.radius * cos(this.apos.z));
      this.dycogx = abs((this.height/2) * cos(this.apos.x)) + abs(this.radius * sin(this.apos.x));
      if (this.dycogx <= this.dycogz) {
        this.dycog = this.dycogx;
      } else {
        this.dycog = this.dycogz;
      }
      this.perpdz = sqrt((this.diagonal * this.diagonal)-(this.dycogz * this.dycogz));
      //this.torque.z *= this.perpdz;
      //print(this.velocity.x, this.pos.y, this.dycog);
      print(csvFileData);
      this.acceleration.mult(0);
      this.aa.mult(0);
    }

    display() {
      noStroke();
      fill(255, 20, 190);
      translate(-width/2 + this.radius, -height/2);
      translate(this.pos.x, this.pos.y, this.pos.z);
      rotateX(this.apos.x);
      rotateY(this.apos.y);
      rotateZ(this.apos.z);
      cylinder(this.radius, this.height);
    }

    bouncing(torque) {
      if (this.pos.y >= height - this.dycog) {
        this.velocity.y *= e;
        this.pos.y = height - this.dycog;
        //csvFileData = csvFileData + '\n';
        t = millis;
        ax = this.apos.x;
        ay = this.apos.y;
        az = this.apos.z;
        t = t.toString();
        ax = ax.toString();
        ay = ay.toString();
        az = az.toString();
        csvFileData =  csvFileData + t + ',' + ax + ',' + ay + ',' + az;

        //Adding torque to angular velocity
        if ((this.apos.z % PI !== 0) && ((this.apos.z - PI/2) % PI !== 0)) {
          this.aa.z += this.torque.z * 20;
        }

      }
      if (this.pos.x >= width - this.dxcogz) {
        this.velocity.x *= e;
        this.pos.x = width - this.dxcogz;
      }
      if (this.pos.x < 0) {
        this.velocity.x *= e;
        this.pos.x = 0;
      }
    }
};

function draw() {
  background(254, 255, 219);

  //Gravity
  gravity = createVector(0 , g * coin.mass, 0);
  coin.applyForce(gravity);

  //Drag
  // var drag = coin.velocity.copy();
  // drag.mag(drag.mag() * drag.mag());
  // drag.mult(-0.5);
  // drag.mult(rho * coin.area * cd);
  // coin.applyForce(drag);

  //Surface friction
 if (coin.pos.y >= height - coin.dycog) {
    var normal = gravity.y;
    var friction = createVector(coin.velocity.x, 0, coin.velocity.z);
    friction.mult(-1);
    friction.normalize();
    var frictionMag =  normal * mu;
    friction.mult(frictionMag);
    coin.applyForce(friction);
  }
  moment = coin.torque.z * coin.perpdz;
  coin.display();
  coin.bouncing(moment);
  coin.update();
}