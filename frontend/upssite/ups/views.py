import datetime

from django.conf import settings
from django.contrib.auth.decorators import login_required
from django.contrib.auth.forms import UserCreationForm
from django.contrib import messages
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.models import User
from django.core.mail import send_mail
from django.shortcuts import render, redirect
from .form import CreateUserForm, UserCreationForm1
from django.template import context

from .with_database import get_shipment_status, get_package_list, get_item_list, get_package_id_list, \
    get_selected_package_id_list, get_selected_package_list
from .with_backend import handleF2BChangeAddress, s, host, port


@login_required(login_url='login')
def homePage(request):
    print('home page of ups')
    context = {'user_id': request.user.id}
    if request.method == 'POST':
        if 'tracking_number' in request.POST:
            tracking_number = request.POST.get('tracking_number')
            if tracking_number != '':
                shipment_status = get_shipment_status(tracking_number)
                if shipment_status is None:
                    messages.error(request, 'tracking number is incorrect')
                else:
                    return render(request, 'home.html', {'user_id': request.user.id, 'status': shipment_status})
            else:
                messages.error(request, 'tracking number is incorrect')
    return render(request, 'home.html', context)


def loginPage(request):
    print('log in page of ups')
    if request.user.is_authenticated:
        return redirect('home')
    else:
        if request.method == 'POST':
            if 'username' in request.POST:
                username = request.POST.get('username')
                password = request.POST.get('password')
                user = authenticate(request, username=username, password=password)
                if user is not None:
                    login(request, user)
                    return redirect('home')
                else:
                    messages.error(request, 'username or password is incorrect')
            elif 'tracking_number' in request.POST:
                tracking_number = request.POST.get('tracking_number')
                if tracking_number != '':
                    shipment_status = get_shipment_status(tracking_number)
                    if shipment_status is None:
                        messages.error(request, 'tracking number is incorrect')
                    else:
                        return render(request, 'login.html', {'status': shipment_status})
                else:
                    messages.error(request, 'tracking number is incorrect')
        return render(request, 'login.html', {})


def signupPage(request):
    if request.method == "POST":
        email = request.POST['email']
        # if User.objects.filter(username=email):
        #     messages.error(request, "Email already used!")
        #     return redirect('home')
        passwd = request.POST['pass1']
        passwd2 = request.POST['pass2']
        if passwd != passwd2:
            messages.error(request, "Passwords should be the same!")
            return redirect('signup')
        # phone = request.POST['phone']
        username = request.POST['username']

        myuser = User.objects.create_user(username, email, passwd)

        myuser.save()

        messages.success(request, "Your Account has been successfully created")

        return redirect('login')

    return render(request, 'signup.html')


def logoutUser(request):
    logout(request)
    return redirect('login')


def shipmentStatus(request):
    return render(request, 'shipment_status.html')


def packages(request):
    if request.method == "POST":
        if 'package_id' in request.POST:
            packages_id = request.POST['package_id']
            new_x = request.POST['new_x']
            new_y = request.POST['new_y']
            shipid, result = handleF2BChangeAddress(packages_id, new_x, new_y)
            if result == 1:
                messages.success(request, "Successfully change the destination of package " + str(shipid) + "!")
                send_mail(
                    "You have a request to change the destination of package " + str(shipid) + "!",
                    "Your request has been confirmed! The destination is now (" + str(new_x) + "," + str(new_y) + ")",
                    settings.EMAIL_HOST_USER,
                    [request.user.email]
                )
            else:
                messages.error(request, "Fail to change the destination of " + str(shipid) + "!")
                send_mail(
                    "You have a request to change the destination of package " + str(shipid) + "!",
                    "Your request has been declined!",
                    settings.EMAIL_HOST_USER,
                    [request.user.email]
                )
        if 'item_name' in request.POST:
            item_name = request.POST['item_name']
            package_id_list = get_selected_package_id_list(request.user.username, item_name)
            package_list = get_selected_package_list(request.user.username, package_id_list)
            all_item_list = []
            for package_id in package_id_list:
                item_list = get_item_list(package_id)
                all_item_list.append(item_list)
            return render(request, 'packages.html', {'user_id': request.user.username, 'package_list': package_list,
                                                     'all_item_list': all_item_list})
        return redirect('packages')

    package_list = get_package_list(request.user.username)
    package_id_list = get_package_id_list(request.user.username)
    all_item_list = []
    for package_id in package_id_list:
        item_list = get_item_list(package_id)
        all_item_list.append(item_list)
    return render(request, 'packages.html', {'user_id': request.user.username, 'package_list': package_list,
                                             'all_item_list': all_item_list})


