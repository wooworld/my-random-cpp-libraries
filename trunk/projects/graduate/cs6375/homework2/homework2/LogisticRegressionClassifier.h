#ifndef LOGISTIC_REGRESSION_CLASSIFIER_H
#define LOGISTIC_REGRESSION_CLASSIFIER_H

#include <map>
#include <vector>
#include <string>
#include "DataSet.h"
#include "Document.h"
#include "Classifier.h"

using namespace std;


class LogisticRegressionClassifier : public Classifier {
public:
  void train( const DataSet& data );
  float test( const DataSet& data );
  unsigned int classify( const Document& doc );  

protected:  
  void gradientAscent( const DataSet& data );
  float conditionalAPosteriori( string x_i, const DataSet& data );
  float pHat( map<string, unsigned int>& docVocab );

  map<string, float> m_weights;
};

#endif

/*function classify(X = bagOfWordsForThisExample, W = weights)
{
   return w0 + w1*x1 + ... + wN*xN > 0 ? 0 : 1
}

The real work is coming up with the weights (one for each word in the vocab):

W = weights
W0 = some value?

//gradient ascent with hard limit
for someHardLimit 
{
   for each i in W.size
      Wi = Wi - (0.1)* conditionalAPosteriori(i)
}

function pHat(X)
{
   for each Wi in weights (i = 1..N)
      sum += Wi * Xi

   temp = e^(W0 + sum)
   return temp / (1 + temp)
}

function conditionalAPosteriori(i)
{
   W = weights
   int sum = 0;

   for each j in numOfTrainingExamples
   {
      X = bag of words from training example j
      sum += Xi * (yj - pHat(X))  //----- I don't understand what yj is supposed to be here??
   }

   //L2 regularization
   return -alpha*Wi^2 + sum //try different values of alpha here
}*/