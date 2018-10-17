from django.conf.urls import url
from django.conf import settings
from django.conf.urls.static import static

from . import views

urlpatterns = [
    # ex: /polls/
    url(r'^$', views.index, name='index'),

 	
 	#url linking to function calls in view.py

    url(r'^games/$', views.index, name='games'),

    url(r'^simon/$', views.simon, name='simon'),

    url(r'^story/$', views.story, name='story'),

    url(r'^support/$', views.support, name='support'),



    # ex: /polls/5/
    url(r'^(?P<question_id>[0-9]+)/$', views.test2, name='test2'),
    # ex: /polls/5/results/
    # url(r'^(?P<question_id>[0-9]+)/results/$', views.results, name='results'),
    # ex: /polls/5/vote/
    url(r'^(?P<question_id>[0-9]+)/vote/$', views.vote, name='vote'),
]