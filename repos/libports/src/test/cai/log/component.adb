
with Cai.Log;
with Cai.Log.Client;

procedure Component
is
   Log : Cai.Log.Client_Session := Cai.Log.Client.Create;
   I : constant Integer := 42;
   L : constant Long_Integer := 4398046511104;
   NI : constant Integer := -42;
   NL : constant Long_Integer := -4398046511104;
   U : constant Cai.Log.Unsigned := 16#deadbeef#;
   Log2 : Cai.Log.Client_Session := Cai.Log.Client.Create;
begin
   Cai.Log.Client.Initialize (Log, "Cai Log Test");
   Cai.Log.Client.Initialize (Log2, "Another log client");
   Cai.Log.Client.Info (Log, "Info message");
   Cai.Log.CLient.Warning (Log, "Warning message");
   Cai.Log.Client.Error (Log, "Error message");
   Cai.Log.Client.Info (Log2, "Message from another log client");
   Cai.Log.Client.Info (Log, "Integer: " & Cai.Log.Image (I));
   Cai.Log.Client.Info (Log, "Negative Integer: " & Cai.Log.Image (NI));
   Cai.Log.Client.Info (Log, "Long_Integer: " & Cai.Log.Image (L));
   Cai.Log.Client.Info (Log, "Negative Long_Integer: " & Cai.Log.Image (NL));
   Cai.Log.Client.Info (Log, "Smallest Integer: " & Cai.Log.Image (Integer'First));
   Cai.Log.Client.Info (Log, "Smallest Long_Integer: " & Cai.Log.Image (Long_Integer'First));
   Cai.Log.Client.Info (Log, "Largest Integer: " & Cai.Log.Image (Integer'Last));
   Cai.Log.Client.Info (Log, "Largest Long_Integer: " & Cai.Log.Image (Long_Integer'Last));
   Cai.Log.Client.Info (Log, "True: " & Cai.Log.Image (True));
   Cai.Log.Client.Info (Log, "False: " & Cai.Log.Image (False));
   Cai.Log.Client.Info (Log, "Hex value: " & Cai.Log.Image (U));
   Cai.Log.Client.Info (Log, "Smallest hex value: " & Cai.Log.Image (Cai.Log.Unsigned'First));
   Cai.Log.Client.Info (Log, "Largest hex value: " & Cai.Log.Image (Cai.Log.Unsigned'Last));
   Cai.Log.Client.Finalize (Log);
   Cai.Log.Client.Finalize (Log2);
end Component;
