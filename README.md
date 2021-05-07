# Data_Engineering_Dott
Welcome to my solution to the Dott data engineering test.
Here I will explain some of my thought processes on tool selection and logic decision making. 

The tools I have used
	*  PostgreSQL and pgAdmin4
	*  AWS S3

I have chosen PostgreSQL as the database to work with because it is an SQL database that is easily extensible. Within the scope of this project it was unclear to me which extensions and functionalities would be necessary since I hadn’t worked with SQL or data in general before. To use an advanced and well documented open source database seemed like the right choice. 

By setting up a free AWS account I was able to create a pipeline which would make a back-up of the data that would be replaced everyday. I designed the queries in a way so they would only store the necessary data to answer the questions. Saving all the raw data externally and not just the unused data seemed to me the most beneficial way if the analysts needed answering to other questions in the future. 


Seen in below diagram, the CSV-files are daily updated in the background to an AWS S3 bucket so not to lose any valuable data. While these files are uploaded the script will import the new CSV files into their respective tables, using deduplication logic and only saving necessary data. 
After these tables are updated, the script will update the main table (b_total_rides_info), which in its turn can answer the question the analysts are asking. 

![Creating_main_table3](https://user-images.githubusercontent.com/58388142/117368978-93b70400-aec4-11eb-94ed-0b33396008cd.png)


Below is a diagram showing the connections the queries are using to answer the questions. Supporting tables are used (a_dates_in_join and b_dates_customer_segment) to fill the gaps for missing values.  

![Creating_table_questions](https://user-images.githubusercontent.com/58388142/117368973-9154aa00-aec4-11eb-9c56-94da7fb0daeb.png)

The Questions:
Questions 1. What is the daily rider frequency distribution?
  c_frequency_distribution

Most of the High-frequent riders only fall in this frequency in their first day.
This is because the calculation uses the users day of creation as the start date to calculate the average. 
The numbers are also skewed in the different direction because the data doesn’t have a “deletedAt” column. Because this is missing, riders will fall under the Low-frequent-rider into eternity when have only used Dott services perhaps once. 
To look for a better distribution of rider frequency one could not take the users which fall under “New Riders” and “Inactive” of the Customer Segment into account to find a more sustainable distribution. 

Questions 2. What is the monthly frequency for preferred week days? 
c_monthly_distribution_preferred_day

  The data here seems to be quite accurate since all the data came from a single month.
A supporting table was used with the ‘dates of June 2019’ and ‘if the date was a weekday or weekend’ to easily join tables in the necessary query.

Questions 3. What is the growth rate (%) of each customer segment week-to-week? 
c_growth_rate_by_segment

  This table only shows relevant data starting at the 2019-06-15, making the first 14 days of which there was data incorrect. This is because the query needs to look 1 to 14 days of past data per user.
	Except for the segment 'New Rider’, here the relevant data starts at 2019-06-08. Because this segment doesn’t use rides but is only concerned about the date of creation, But then again, there is only available data of users who used dots services in June, which make these numbers incomplete again. 

Questions 4. What is the total, maximum, average and minimum ride distance by rider frequency? 
c_distance_by_rider_frequency

  The distances are calculated from begin to end point, not taking detours into account. Also there are over a 170 rides of distances 0.0 and only slowly increasing from that point. These are probably failed rides. I suggest setting up a filter for failed rides, which will ask for a minimum distance for a ride to fall under the segment. If riders circle around and drop the scooter into a spot under this distance, booking_amount, time_ride_start and time_ride_end could be used to then NOT filter these rides.  
 
Points of improvement:
	I took the rider frequency per rider per DAY and not per ride. When calculating the 		distances the rider could be a Low-frequent rider at the start of the day and a High-frequent rider at the end of the day. My calculations will let these distances fall under what the frequency is at the end of the day. 

Questions 5. How many days, on average, do our customers stay in the ‘Active’ segment? 
c_consecutive_days_active_average

  Here the average should be slightly higher since the active segment starts at 2019-06-08 and there could have been consecutive Active users before this date. 


General improvements of my work: 
Doing this assignment shed some light on the fast amount of data tooling there is out there. Especially interesting tools like Hadoop, Airflow, Kafka or PgTap.
If time would not be of essence I would love to dive into these systems, see how they work and learn why or why not to implement them for certain tasks. 

I would also love to implement a data visualizer, although this might be more the job for the analyser. They could be used to easily find mistakes in the query logic, plus graphs are awesome. 
