package launcher;



public interface ComboItemRemovedListener
{
	public void comboItemRemoved(Object removed);
	
	public class RemovedEvent
	{
		private Object removed;
		
		public RemovedEvent(Object objectRemoved)
		{
			this.removed = objectRemoved;
		}
		
		public Object getRemovedObject() {return removed;}
	}
}
