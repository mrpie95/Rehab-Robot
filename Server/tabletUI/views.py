# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render

from django.http import HttpResponse

from django.template import loader

from django.shortcuts import render

# from .models import Question



def index(request):
    return render(request, 'rehabrobot/games_page.html')


def test2(request):
    print "works :)"
    return HttpResponse("<h1>alalalala fuck america</h1>")


def simon(request):

    if request.method == 'POST':

        move = request.POST.get('move')
        durationStr = request.POST.get('duration')

        duration = 0;



        if durationStr == '1 min':
            print('duration set to 1 min')
            duration = 1;
        elif durationStr == '2 mins':
            print('duration set to 2 min')
            duration = 2;
        elif durationStr == '5 mins':
            print('duration set to 5 min')
            duration = 5;

        if duration > 0:
            if move == 'bend knees':
                print('simons says bend knees')
                # call bend knee functio method

            elif move == 'raise right arm':
                print('simons says raise right arm')
                # call raise right arm function method

            elif move == 'raise left leg':
                print('simons says raise left leg')
                # call raise left leg function method
        else:
            print('invalid time duration')

    return render(request, 'rehabrobot/simons_page.html')

def story(request):
    
    if request.method == 'POST':

        story = request.POST.get('story')

        if story == 'story1':
            print('playing story 1')
            # call story method

        elif story == 'story2':
            print('playing story 2')
            # call story method`

        elif story == 'story3':
            print('playing story 3')
            # call story method

        elif story == 'story4':
            print('playing story 4')
            # call story method

        elif story == 'story5':
            print('playing story 5')
            # call story method

        elif story == 'story6':
            print('playing story 6')
            # call story method 

    return render(request, 'rehabrobot/story_page.html')

def support(request):
    return render(request, 'rehabrobot/support_page.html')

def detail(request, question_id):

    return HttpResponse("You're looking at question %s." % question_id)

def results(request, question_id):
    response = "You're looking at the results of question %s."
    return HttpResponse(response % question_id)

def vote(request, question_id):
    return HttpResponse("You're voting on question %s." % question_id)