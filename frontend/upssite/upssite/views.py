import datetime
from django.contrib.auth.forms import UserCreationForm
from django.contrib import messages
from django.contrib.auth import authenticate, login, logout
from django.shortcuts import render, redirect
from django.template import context

def homePage(request):
    print('home page of ups')
    return render(request, 'home.html', context)

def loginPage(request):
    print('log in page of ups')
    if request.user.is_authenticated:
        return redirect('home')
    else:
        if request.method == 'POST':
            username = request.POST.get('username')
            password = request.POST.get('password')
            user = authenticate(request, username=username, password=password)
            if user is not None:
                login(request, user)

                return redirect('home')
        else:
            messages.info(request, 'username or password is incorrect')

        context = {}
        return render(request, 'login.html', context)

def registerPage(request):
    print('register page of ups')
    if request.user.is_authenticated:
        return redirect('home')
    else:
        form = UserCreationForm()
        if request.method == 'POST':
            form = UserCreationForm(request.POST)
            if form.is_valid():
                user = form.save()
                messages.success(request, "account was created for " + request.user.username)
                return redirect('login')
            else:
                messages.info(request, form.error_messages)
        context = {'form': form}
        return render(request, 'register.html', context)

def logoutUser(request):
    logout(request)
    return redirect('login')


