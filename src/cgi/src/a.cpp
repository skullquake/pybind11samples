#include<iostream>
#include<pybind11/embed.h>
	//cpp
#include<regex>
#include<string>
namespace py=pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::module m=pybind11::module::import("__main__");
	pybind11::object s=m.attr("__dict__");
	//script
	pybind11::exec(
		R"(
import sys;
import os;
import cgi,cgitb;
import datetime;
form=cgi.FieldStorage();
sys.stdout.write('Set-Cookie:UserID = XYZ;\r\n');
sys.stdout.write('Set-Cookie:Password = %s;\r\n' % 'qwerasdfzxcv');
#sys.stdout.write('Set-Cookie:Expires = %s;\r\n' % datetime.now().strftime("%Y%m%d"));
sys.stdout.write('Set-Cookie:Domain = localhost:8080/cgi-bin/a.out;\r\n');
sys.stdout.write('Set-Cookie:Path = /perl;\r\n');
sys.stdout.write('Content-type:text/html\r\n\r\n');
sys.stdout.write('<html>');
sys.stdout.write('	<head>');
sys.stdout.write('		<meta name="viewport" content="width=device-width,initial-scale=1,scrhink-to-fit=no">');
sys.stdout.write('		</meta>');
sys.stdout.write('		<title>');
sys.stdout.write('			pybind11 cgi');
sys.stdout.write('		</title>');
sys.stdout.write('		<link rel="stylesheet" href="https://bootswatch.com/4/slate/bootstrap.css"></link>');
sys.stdout.write('		<script src="https://bootswatch.com/_vendor/jquery/dist/jquery.min.js"></script>');
sys.stdout.write('		<script src="https://bootswatch.com/_vendor/popper.js/dist/umd/popper.min.js"></script>');
sys.stdout.write('		<script src="https://bootswatch.com/_vendor/bootstrap/dist/js/bootstrap.min.js"></script>');
sys.stdout.write('		<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/prism/1.17.1/themes/prism-twilight.min.css"></link>');
sys.stdout.write('		<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.17.1/components/prism-core.min.js"></script>');
sys.stdout.write('		<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.17.1/plugins/autoloader/prism-autoloader.min.js"></script>');
sys.stdout.write('		<style>');
sys.stdout.write('			body{margin-top:120px;}');
sys.stdout.write('		</style>');
sys.stdout.write('	</head>');
sys.stdout.write('	<body>');
#--------------------------------------------------------------------------------
sys.stdout.write('		<div class="navbar navbar-expand-lg fixed-top navbar-dark bg-primary">');
sys.stdout.write('			<div class="container">');
sys.stdout.write('				<a href="#" class="navbar-brand">');
sys.stdout.write('					pybind11 cgi');
sys.stdout.write('				</a>');
sys.stdout.write('				<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarResponsive">');
sys.stdout.write('					<span class="navbar-toggler-icon">');
sys.stdout.write('					</span>');
sys.stdout.write('				</button>');
sys.stdout.write('				<div id="navbarResponsive" class="collapse navbar-collapse">');
sys.stdout.write('					<ul class="navbar-nav">');
sys.stdout.write('						<li class="nav-item">');
sys.stdout.write('							<a class="nav-link">');
sys.stdout.write('								Test');
sys.stdout.write('							</a>');
sys.stdout.write('						</li>');
sys.stdout.write('					</ul>');
sys.stdout.write('				</div>');
sys.stdout.write('			</div>');
sys.stdout.write('		</div>');
#--------------------------------------------------------------------------------
sys.stdout.write('		<div class="container">');
sys.stdout.write('			<h3>Python CGI</h3>\n');
#--------------------------------------------------------------------------------
print('<p>');
print('	<button class="btn btn-primary" type="button" data-toggle="collapse" data-target="#collapse_os_environ_keys" aria-expanded="false" aria-controls="collapse_os_environ_keys">');
print('		os.environ');
print('	</button>');
print('</p>');
print('<div class="collapse" id="collapse_os_environ_keys">');
sys.stdout.write('			<pre><code class="language-javascript">');
for param in os.environ.keys():
	sys.stdout.write('			%s: %s\n' % (param,os.environ[param]))
sys.stdout.write('</code></pre>');
print('</div>');
#--------------------------------------------------------------------------------
sys.stdout.write('		<h4>cgi.FieldStorage</h4>');
#if form.has_key('foo'):
#	sys.stdout.write('foo: %s\n' % form.getvalue('foo'));
#else:
#	sys.stdout.write('		foo: null</br>\n');
#--------------------------------------------------------------------------------
print('<p>');
print('	<button class="btn btn-primary" type="button" data-toggle="collapse" data-target="#collapse_form_keys" aria-expanded="false" aria-controls="collapse_form_keys">');
print('		form.keys()');
print('	</button>');
print('</p>');
print('<div class="collapse" id="collapse_form_keys">');
sys.stdout.write('		<pre><code class="language-javascript">');
for a in form.keys():
	sys.stdout.write('	%s:%s\n' % (a,form.getvalue(a)));
sys.stdout.write('</code></pre>');
print('</div>');
#--------------------------------------------------------------------------------
print('<h3>\n');
print('	GET\n');
print('</h3>\n');
print('<form action="/cgi-bin/a.out" method="get">\n');
print('	<div class="form-group">\n');
print('		<label for="exampleInputEmail1">Email address</label>\n');
print('		<input type="email" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp" name="email">\n');
print('		<small id="emailHelp" class="form-text text-muted">Well never share your email with anyone</small>\n');
print('	</div>\n');
print('	<div class="form-group">\n');
print('		<label for="exampleInputPassword1">Password</label>\n');
print('		<input type="password" class="form-control" id="exampleInputPassword1" placeholder="Password" name="password">\n');
print('	</div>\n');
print('	<div class="form-group form-check">\n');
print('		<input type="checkbox" class="form-check-input" id="exampleCheck1" name="checkout">\n');
print('		<label class="form-check-label" for="exampleCheck1">Check me out</label>\n');
print('	</div>\n');
print('	<button type="submit" class="btn btn-primary">Submit</button>\n');
print('</form>\n');
#--------------------------------------------------------------------------------
print('<h3>\n');
print('	POST\n');
print('</h3>\n');
print('<form action="/cgi-bin/a.out" method="post">\n');
print('	<div class="form-group">\n');
print('		<label for="exampleInputEmail1">Email address</label>\n');
print('		<input type="email" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp" name="email">\n');
print('		<small id="emailHelp" class="form-text text-muted">Well never share your email with anyone</small>\n');
print('	</div>\n');
print('	<div class="form-group">\n');
print('		<label for="exampleInputPassword1">Password</label>\n');
print('		<input type="password" class="form-control" id="exampleInputPassword1" placeholder="Password" name="password">\n');
print('	</div>\n');
print('	<div class="form-group form-check">\n');
print('		<input type="checkbox" class="form-check-input" id="exampleCheck1" name="checkout">\n');
print('		<label class="form-check-label" for="exampleCheck1">Check me out</label>\n');
print('	</div>\n');
print('	<button type="submit" class="btn btn-primary">Submit</button>\n');
print('</form>\n');
#--------------------------------------------------------------------------------

sys.stdout.write('		<script>');
sys.stdout.write('			Prism.highlighAll();');
sys.stdout.write('		</script>');
sys.stdout.write('	</body>');
sys.stdout.write('</html>');
		)",
		s
	);
	return 0;
}


