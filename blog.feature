#define TODAY = GET_TODAY()
#define A_MONTH_AGO = TODAY_OFFSET_BY(-30)
Given a transaction is authorised on A_MONTH_AGO
And the transaction was not charged 
When the cancellation job runs for TODAY
Then the authorisation should be cancelled

#define A_MONTH_AGO_A 8 October 2020
#define CANCELLATION_DATE 9 November 2020
Given a transaction is authorised on A_MONTH_AGO_A
And the transaction was not charged
When the cancellation job runs for CANCELLATION_DATE
Then the authorisation should be cancelled

Given a transaction was authorised more than a month ago 
And the transaction was not charged 
When the cancellation job runs
Then the authorisation should be cancelled

#define TIME_OF_AUTHORIZATION 2020-10-09T14:27:46.000Z
#define TIME_OF_CANCELLATION_JOB 2020-11-09T14:27:46.001Z
Given the current time is TIME_OF_AUTHORIZATION
And a transaction is authorised
When the current time is TIME_OF_CANCELLATION_JOB
And the transaction was not charged
And the cancellation job runs
Then the authorisation should be cancelled