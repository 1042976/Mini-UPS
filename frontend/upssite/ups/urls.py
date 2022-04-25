from django.urls import path
from . import views
urlpatterns = [
    path('home', views.homePage, name='home'),
    path('login', views.loginPage, name='login'),
    #path('register', views.registerPage, name='register'),
    path('signup', views.signupPage, name='signup'),
    path('logout', views.logoutUser, name='logout'),
    path('shipment_status', views.shipmentStatus, name='shipment_status'),
    path('packages', views.packages, name='packages'),
]