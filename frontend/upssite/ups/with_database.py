from django.db import connection
from collections import namedtuple


def namedtuplefetchall(cursor):
    """Return all rows from a cursor as a namedtuple"""
    desc = cursor.description
    nt_result = namedtuple('Result', [col[0] for col in desc])
    return [nt_result(*row) for row in cursor.fetchall()]


def get_shipment_status(package_id):
    with connection.cursor() as cursor:
        cursor.execute("SELECT STATUS FROM PACKAGE WHERE PACKAGE_ID = %s", [package_id])
        row = cursor.fetchone()
        if row is not None:
            return row[0]
    return None


def get_package_list(username):
    with connection.cursor() as cursor:
        cursor.execute("SELECT * FROM PACKAGE WHERE USERNAME = %s", [username])
        results = namedtuplefetchall(cursor)
        if results is not None:
            return results
    return None


def get_package_id_list(username):
    with connection.cursor() as cursor:
        cursor.execute("SELECT PACKAGE_ID FROM PACKAGE WHERE USERNAME = %s", [username])
        row = cursor.fetchall()
        if row is not None:
            return [r[0] for r in row]
    return None


def get_item_list(package_id):
    with connection.cursor() as cursor:
        cursor.execute("SELECT * FROM ITEM WHERE PACKAGE_ID = %s ORDER BY NAME ", [package_id])
        results = namedtuplefetchall(cursor)
        if results is not None:
            return results
    return None

def get_selected_package_list(username, package_id_list):
    id_list_str = "("
    for package_id in package_id_list:
        id_list_str += str(package_id)
        id_list_str += ","
    id_list_str = id_list_str[:-1]
    id_list_str += ")"
    with connection.cursor() as cursor:
        for package_id in package_id_list:
            cursor.execute("SELECT * FROM PACKAGE WHERE PACKAGE_ID IN " + id_list_str)
            results = namedtuplefetchall(cursor)
            if results is not None:
                return results
    return None

def get_selected_package_list_with_status(username, package_id_list, package_status):
    id_list_str = "("
    for package_id in package_id_list:
        id_list_str += str(package_id)
        id_list_str += ","
    id_list_str = id_list_str[:-1]
    id_list_str += ")"
    with connection.cursor() as cursor:
        for package_id in package_id_list:
            cursor.execute("SELECT * FROM PACKAGE WHERE PACKAGE_ID IN " + id_list_str + " AND STATUS = \'" +
                           package_status + "\'")
            results = namedtuplefetchall(cursor)
            if results is not None:
                return results
    return None

def get_selected_package_id_list(username, itemname):
    with connection.cursor() as cursor:
        cursor.execute("SELECT PACKAGE_ID FROM ITEM WHERE NAME = %s ", [itemname])
        row = cursor.fetchall()
        if row is not None:
            return [r[0] for r in row]
    return None
