from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def homepage():

    with app.open_resource('count.txt') as f:
        laundry_count = f.read()

    with app.open_resource('ava.txt') as f2:
        ava = f2.read()

    with app.open_resource('left.txt') as f3:
        left = f3.read()

    with app.open_resource('right.txt') as f4:
        right = f4.read()

    return render_template('index.html', laundry_count = laundry_count, num = ava, left_stat = left, right_stat = right)


@app.route('/index')
def index():
    with app.open_resource('count.txt') as f:
        laundry_count = f.read()

    with app.open_resource('ava.txt') as f2:
        ava = f2.read()

    with app.open_resource('left.txt') as f3:
        left = f3.read()

    with app.open_resource('right.txt') as f4:
        right = f4.read()

    return render_template('index.html', laundry_count = laundry_count, num = ava, left_stat = left, right_stat = right)

@app.route('/news')
def news():
    return render_template('news.asp')
    return('hello')
@app.route('/contact')
def contact():
    return render_template('contact.html')

@app.route('/about')
def about():
    return render_template('about.html')

if __name__ == "__main__":
    app.run()
